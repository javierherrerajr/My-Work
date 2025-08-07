import { render, screen } from '@testing-library/react';
import Carousel from '../Carousel';

// Mock the Swiper components
jest.mock('swiper/react', () => ({
  Swiper: ({ children, className }: { children: React.ReactNode; className?: string }) => (
    <div data-testid="swiper" className={className}>
      {children}
    </div>
  ),
  SwiperSlide: ({ children, className }: { children: React.ReactNode; className?: string }) => (
    <div data-testid="swiper-slide" className={className}>
      {children}
    </div>
  ),
}));

// Mock the Swiper modules
jest.mock('swiper/modules', () => ({
  Navigation: {},
}));

describe('Carousel', () => {
  const mockItems = [
    { classId: 'CS100', difficulty: 3.5, href: '/courses/CS100' },
    { classId: 'CS101', difficulty: 4.0, href: '/courses/CS101' },
    { classId: 'CS102', difficulty: 4.5, href: '/courses/CS102' },
  ];

  it('renders all items', () => {
    render(<Carousel items={mockItems} />);
    
    const slides = screen.getAllByTestId('swiper-slide');
    expect(slides).toHaveLength(3);
  });

  it('renders correct content for each item', () => {
    render(<Carousel items={mockItems} />);
    
    mockItems.forEach(item => {
      expect(screen.getByText(item.classId)).toBeInTheDocument();
      expect(screen.getByText(item.difficulty.toFixed(1))).toBeInTheDocument();
    });
  });

  it('renders links with correct hrefs', () => {
    render(<Carousel items={mockItems} />);
    
    mockItems.forEach(item => {
      const link = screen.getByText(item.classId).closest('a');
      expect(link).toHaveAttribute('href', item.href);
    });
  });

  it('applies correct styling classes', () => {
    render(<Carousel items={mockItems} />);
    
    const swiper = screen.getByTestId('swiper');
    expect(swiper).toHaveClass('py-4');
    
    const slides = screen.getAllByTestId('swiper-slide');
    slides.forEach(slide => {
      expect(slide).toHaveClass('flex', 'justify-center', 'items-center');
    });
    
    const links = screen.getAllByRole('link');
    links.forEach(link => {
      expect(link).toHaveClass(
        'flex',
        'flex-col',
        'justify-center',
        'items-center',
        'bg-[#d6e2ce]',
        'text-[#3a2c23]',
        'rounded-xl',
        'aspect-square',
        'shadow-lg',
        'hover:shadow-xl',
        'transition',
        'duration-300',
        'hover:underline'
      );
    });
  });

  it('renders Swiper with correct props', () => {
    render(<Carousel items={mockItems} />);
    
    const swiper = screen.getByTestId('swiper');
    expect(swiper).toBeInTheDocument();
  });

  it('handles empty items array', () => {
    render(<Carousel items={[]} />);
    
    const slides = screen.queryAllByTestId('swiper-slide');
    expect(slides).toHaveLength(0);
  });

  it('renders difficulty with one decimal place', () => {
    const itemsWithDecimals = [
      { classId: 'CS100', difficulty: 3.333, href: '/courses/CS100' },
      { classId: 'CS101', difficulty: 4.666, href: '/courses/CS101' },
    ];
    
    render(<Carousel items={itemsWithDecimals} />);
    
    expect(screen.getByText('3.3')).toBeInTheDocument();
    expect(screen.getByText('4.7')).toBeInTheDocument();
  });
}); 