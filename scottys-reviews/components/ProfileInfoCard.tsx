// components/ProfileInfoCard.tsx
interface ProfileInfoCardProps {
  user: {
    name: string;
    email: string;
    major: string;
    startYear: number;
    expectedGradYear: number;
    status: string;
  };
}

export const ProfileInfoCard: React.FC<ProfileInfoCardProps> = ({ user }) => {
  return (
    <div className="bg-white shadow-sm border p-6 rounded-lg">
      <h2 className="text-xl font-bold mb-2">My Profile</h2>
      <ul className="space-y-1 text-sm text-gray-700">
        <li><strong>Name:</strong> {user.name}</li>
        <li><strong>Email:</strong> {user.email}</li>
        <li><strong>Major:</strong> {user.major}</li>
        <li><strong>Start Year:</strong> {user.startYear}</li>
        <li><strong>Expected Graduation:</strong> {user.expectedGradYear}</li>
        <li><strong>Status:</strong> {user.status}</li>
      </ul>
    </div>
  );
};

