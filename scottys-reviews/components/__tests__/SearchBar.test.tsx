import { render, screen, fireEvent, waitFor } from '@testing-library/react';
import userEvent from '@testing-library/user-event';
import { SearchBar } from '../SearchBar';
import '@testing-library/jest-dom';
import { jest, describe, it, expect } from '@jest/globals';

// Mock the fetch function
global.fetch = jest.fn();

// Mock the router
const mockPush = jest.fn();
jest.mock('next/navigation', () => ({
  useRouter: () => ({
    push: mockPush,
  }),
}));

describe('SearchBar', () => {
  const mockOnSearch = jest.fn();

  beforeEach(() => {
    jest.clearAllMocks();
    mockOnSearch.mockClear();
  });

  it('renders with default placeholder', () => {
    render(<SearchBar />);
    expect(screen.getByPlaceholderText('Search for classes here')).toBeInTheDocument();
  });

  it('renders with custom placeholder', () => {
    const customPlaceholder = 'Custom placeholder';
    render(<SearchBar placeholder={customPlaceholder} />);
    expect(screen.getByPlaceholderText(customPlaceholder)).toBeInTheDocument();
  });

  it('shows loading state while fetching suggestions', async () => {
    (global.fetch as jest.Mock).mockImplementationOnce(() => 
      new Promise(resolve => setTimeout(() => resolve({
        ok: true,
        json: () => Promise.resolve([])
      }), 100))
    );

    render(<SearchBar />);
    const input = screen.getByRole('textbox');
    await userEvent.type(input, 'CS');

    await waitFor(() => {
      expect(screen.getByText(/loading/i)).toBeInTheDocument();
    });
  });

  it('displays suggestions when API returns results', async () => {
    const mockSuggestions = [
      { courseid: 'CS100', classname: 'Intro to CS', subject: 'Computer Science' },
      { courseid: 'CS101', classname: 'Data Structures', subject: 'Computer Science' }
    ];

    (global.fetch as jest.Mock).mockResolvedValueOnce({
      ok: true,
      json: () => Promise.resolve(mockSuggestions)
    });

    render(<SearchBar />);
    const input = screen.getByRole('textbox');
    await userEvent.type(input, 'CS');

    await waitFor(() => {
      const suggestions = screen.getAllByRole('listitem');
      expect(suggestions).toHaveLength(2);
      expect(suggestions[0]).toHaveTextContent('CS100');
      expect(suggestions[0]).toHaveTextContent('Intro to CS');
      expect(suggestions[1]).toHaveTextContent('CS101');
      expect(suggestions[1]).toHaveTextContent('Data Structures');
    });
  });

  it('shows "No courses found" when API returns empty results', async () => {
    (global.fetch as jest.Mock).mockResolvedValueOnce({
      ok: true,
      json: () => Promise.resolve([])
    });

    render(<SearchBar />);
    const input = screen.getByRole('textbox');
    await userEvent.type(input, 'XYZ');

    await waitFor(() => {
      expect(screen.getByText('No courses found')).toBeInTheDocument();
    });
  });

  it('handles keyboard navigation', async () => {
    const mockSuggestions = [
      { courseid: 'CS100', classname: 'Intro to CS', subject: 'Computer Science' },
      { courseid: 'CS101', classname: 'Data Structures', subject: 'Computer Science' }
    ];

    (global.fetch as jest.Mock).mockResolvedValueOnce({
      ok: true,
      json: () => Promise.resolve(mockSuggestions)
    });

    render(<SearchBar />);
    const input = screen.getByRole('textbox');
    await userEvent.type(input, 'CS');

    await waitFor(() => {
      const suggestions = screen.getAllByRole('listitem');
      
      // Press arrow down
      fireEvent.keyDown(input, { key: 'ArrowDown' });
      expect(suggestions[0]).toHaveClass('bg-gray-100');

      // Press arrow down again
      fireEvent.keyDown(input, { key: 'ArrowDown' });
      expect(suggestions[1]).toHaveClass('bg-gray-100');

      // Press arrow up
      fireEvent.keyDown(input, { key: 'ArrowUp' });
      expect(suggestions[0]).toHaveClass('bg-gray-100');
    });
  });

  it('closes suggestions when clicking outside', async () => {
    const mockSuggestions = [
      { courseid: 'CS100', classname: 'Intro to CS', subject: 'Computer Science' }
    ];

    (global.fetch as jest.Mock).mockResolvedValueOnce({
      ok: true,
      json: () => Promise.resolve(mockSuggestions)
    });

    render(<SearchBar />);
    const input = screen.getByRole('textbox');
    await userEvent.type(input, 'CS');

    await waitFor(() => {
      expect(screen.getAllByRole('listitem')).toHaveLength(1);
    });

    // Click outside
    fireEvent.mouseDown(document.body);

    await waitFor(() => {
      expect(screen.queryByRole('listitem')).not.toBeInTheDocument();
    });
  });

  it('handles API errors gracefully', async () => {
    (global.fetch as jest.Mock).mockRejectedValueOnce(new Error('API Error'));

    render(<SearchBar />);
    const input = screen.getByRole('textbox');
    await userEvent.type(input, 'CS');

    await waitFor(() => {
      expect(screen.getByText('No courses found')).toBeInTheDocument();
    });
  });

  it('renders search input and button', () => {
    render(<SearchBar onSearch={mockOnSearch} />);
    
    expect(screen.getByPlaceholderText('Search for classes here')).toBeInTheDocument();
    expect(screen.getByRole('button', { name: /search/i })).toBeInTheDocument();
  });

  it('calls onSearch with input value when search button is clicked', async () => {
    render(<SearchBar onSearch={mockOnSearch} />);
    
    const searchInput = screen.getByPlaceholderText('Search for classes here');
    await userEvent.type(searchInput, 'Computer Science');
    
    const searchButton = screen.getByRole('button', { name: /search/i });
    await userEvent.click(searchButton);
    
    expect(mockOnSearch).toHaveBeenCalledWith('Computer Science');
  });

  it('calls onSearch with input value when Enter key is pressed', async () => {
    render(<SearchBar onSearch={mockOnSearch} />);
    
    const searchInput = screen.getByPlaceholderText('Search for classes here');
    await userEvent.type(searchInput, 'Computer Science{enter}');
    
    expect(mockOnSearch).toHaveBeenCalledWith('Computer Science');
  });

  it('clears input after search', async () => {
    render(<SearchBar onSearch={mockOnSearch} />);
    
    const searchInput = screen.getByPlaceholderText('Search for classes here');
    await userEvent.type(searchInput, 'Computer Science');
    
    const searchButton = screen.getByRole('button', { name: /search/i });
    await userEvent.click(searchButton);
    
    expect(searchInput).toHaveValue('');
  });

  it('handles empty search input', async () => {
    render(<SearchBar onSearch={mockOnSearch} />);
    
    const searchButton = screen.getByRole('button', { name: /search/i });
    await userEvent.click(searchButton);
    
    expect(mockOnSearch).not.toHaveBeenCalled();
  });

  it('applies correct styling classes', () => {
    render(<SearchBar onSearch={mockOnSearch} />);
    
    const searchContainer = screen.getByRole('search');
    expect(searchContainer).toHaveClass('flex', 'items-center', 'space-x-2');
    
    const searchInput = screen.getByPlaceholderText('Search for classes here');
    expect(searchInput).toHaveClass('w-full', 'rounded-full', 'px-6', 'py-3', 'text-md', 'font-fredoka', 'font-lg', 'shadow-md', 'focus:outline-none', 'focus:ring-0', 'focus:border-transparent');
    
    const searchButton = screen.getByRole('button', { name: /search/i });
    expect(searchButton).toHaveClass('px-4', 'py-2', 'bg-blue-600', 'text-white', 'rounded-lg');
  });

  it('handles input with special characters', async () => {
    render(<SearchBar onSearch={mockOnSearch} />);
    
    const searchInput = screen.getByPlaceholderText('Search for classes here');
    await userEvent.type(searchInput, 'CS-101 & EE-201');
    
    const searchButton = screen.getByRole('button', { name: /search/i });
    await userEvent.click(searchButton);
    
    expect(mockOnSearch).toHaveBeenCalledWith('CS-101 & EE-201');
  });

  it('handles input with whitespace', async () => {
    render(<SearchBar onSearch={mockOnSearch} />);
    
    const searchInput = screen.getByPlaceholderText('Search for classes here');
    await userEvent.type(searchInput, '  Computer Science  ');
    
    const searchButton = screen.getByRole('button', { name: /search/i });
    await userEvent.click(searchButton);
    
    expect(mockOnSearch).toHaveBeenCalledWith('  Computer Science  ');
  });
}); 